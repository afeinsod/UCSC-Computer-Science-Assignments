(* $Id: bigint.ml,v 1.5 2014-11-11 15:06:24-08 - - $ *)

open Printf

module Bigint = struct

    type sign     = Pos | Neg
    type bigint   = Bigint of sign * int list
    let  radix    = 10
    let  radixlen =  1

    let car       = List.hd
    let cdr       = List.tl
    let map       = List.map
    let reverse   = List.rev
    let strcat    = String.concat
    let strlen    = String.length
    let strsub    = String.sub
    let zero      = Bigint (Pos, [])

    let charlist_of_string str = 
        let last = strlen str - 1
        in  let rec charlist pos result =
            if pos < 0
            then result
            else charlist (pos - 1) (str.[pos] :: result)
        in  charlist last []

    let bigint_of_string str =
        let len = strlen str
        in  let to_intlist first =
                let substr = strsub str first (len - first) in
                let digit char = int_of_char char - int_of_char '0' in
                map digit (reverse (charlist_of_string substr))
            in  if   len = 0
                then zero
                else if   str.[0] = '_'
                     then Bigint (Neg, to_intlist 1)
                     else Bigint (Pos, to_intlist 0)

    let string_of_bigint (Bigint (sign, value)) =
        match value with
        | []    -> "0"
        | value -> let reversed = reverse value
                   in  strcat ""
                       ((if sign = Pos then "" else "-") ::
                        (map string_of_int reversed))
    
    (*rmvzero: takes in a list of ints, removes any "leading" zeroes*)
    let rec rmvzero listy = 
    if List.length listy < 2 then listy else 
    let revlist = List.rev listy
    in if car revlist = 0 then rmvzero (List.rev (cdr revlist))
    else listy

    (* cmp: takes in 2 lists. Returns 0 if equal, -1 if the first list is bigger, 1     if the second list is bigger *)
    let rec cmp list1 list2 = 
        if List.length list1 > List.length list2 then -1
        else if List.length list1 < List.length list2 then 1
        else (*same lengths*)
            if list1 = [] then 0
            else let rest = cmp (cdr list1) (cdr list2) 
                in if rest = 0 
                    then if car list1 > car list2 then -1
                    else if car list1 < car list2 then 1
                    else 0
                else rest 

    (* add': recursive function on 2 lists and a carry int. Returns a list with the 
    sum of the 2 input lists. *)
    let rec add' list1 list2 carry = match (list1, list2, carry) with
        | list1, [], 0       -> list1
        | [], list2, 0       -> list2
        | list1, [], carry   -> add' list1 [carry] 0
        | [], list2, carry   -> add' [carry] list2 0
        | car1::cdr1, car2::cdr2, carry ->
          let sum = car1 + car2 + carry
          in  sum mod radix :: add' cdr1 cdr2 (sum / radix)

    (*sub': recursive function on 2 lists and a carry int. Returns a list with the 
    difference of the 2 input lists. *)
    let rec sub' list1 list2 carry = match (list1, list2, carry) with
        
        | [0], list2, carry   -> []
        | list1, [], 0       -> list1
        | [], list2, carry   -> list2
        | list1, [], carry   -> sub' list1 [carry] 0
        | car1::cdr1, car2::cdr2, carry ->
                let diff = car1 - car2 - carry
              in if diff < 0 
                then rmvzero (10 + diff :: sub' cdr1 cdr2 1)
                else
                    rmvzero (diff :: sub' cdr1 cdr2 0)

    (*add: wrapper function. Calls add' and sub' depending on signs of inputs.
    Returns a bigint*)
    let add (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        if neg1 = neg2
            then Bigint (neg1, add' value1 value2 0)
        else if cmp value1 value2 < 0
          then Bigint (neg1, sub' value1 value2 0)
       else if cmp value1 value2 > 0
          then Bigint (neg2, sub' value2 value1 0)
       else zero

    (*sub: wrapper function. Calls add' and sub' depending on signs of inputs.
    Returns a bigint*)
    let sub (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
    if neg2 = Pos then add (Bigint (neg1, value1)) (Bigint(Neg, value2))
    else add (Bigint (neg1, value1)) (Bigint(Pos, value2))

    (*mul': recursive function on 2 lists and a power of 2. Returns a list with the product of the 2 input lists. *)
    let rec mul' (list1, powerof2, list2) =
        if cmp powerof2 list1 < 0 
            then list1, []
        else let remainder, product = 
            mul' (list1, (add' powerof2 powerof2 0), (add' list2 list2 0))
        in if cmp remainder powerof2 > 0
            then remainder, product
        else (sub' remainder powerof2 0), (add' product list2 0)

    (*mul: wrapper function. Calls mul'. Returns a bigint*)
    let mul (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
    let _, product = mul' (value1, [1], value2) in
        if neg1 = neg2 
            then Bigint (Pos, product)
        else Bigint (Neg, product)

    (*double: takes in a list and doubles the number*)
    let double number = 
        add' number number 0

    (*div': recursive function on a quotient and 2 lists. Returns a list with the quotient and remainder from division of the 2 input lists. *)
    let rec div' (dividend, powerof2, divisor) =
        if cmp divisor dividend < 0
            then [], dividend
    else let quotient, remainder =
             div' (dividend, double powerof2, double divisor)
         in  if cmp remainder divisor > 1
             then quotient, remainder
             else (add' quotient powerof2 0), (sub' remainder divisor 0)

    (*div: wrapper function. Calls div' depending on signs of inputs.
    Returns a bigint*)
    let div (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
        let quotient, _ = div' (value1, [1], value2) 
        in if neg1 = neg2 
            then Bigint (Pos, quotient)
        else Bigint (Neg, quotient)

    (*rem: wrapper function. Calls div' depending on sign of first list.
    Returns a bigint*)
    let rem (Bigint (neg1, value1)) (Bigint (neg2, value2)) = 
        let _, remainder = div' (value1, [1], value2)
        in Bigint (neg1, remainder)

    (*pow': recursive function on a running total and 2 lists. Returns a list with the the first list aised to the power of the secnd list. *)
    let rec power' (base, expt, result) = match expt with
        | []  -> result
        | car::cdr ->
        if car = 0 || car = 2 || car = 4 || car = 6 || car = 8
            then let nexpt, _ = div' (expt, [1], [2])  
            in let _, product = mul' (base, [1], base)
            in power' (product, nexpt, result)
        else let _, prod = mul' (base, [1], result)
            in power' (base, sub' expt [1] 0, prod)

    (*pow: wrapper function. Calls pow' depending on signs of inputs.
    Returns a bigint*)
    let pow (Bigint (neg1, value1)) (Bigint (neg2, value2)) =
        if neg1 = Pos
            then Bigint (Pos, power' (value1, value2, [1]))
        else if (car value2) = 0 || (car value2) = 2 || (car value2) = 4 || (car value2) = 6 || (car value2) = 8
            then Bigint (Pos, power' (value1, value2, [1]))
        else Bigint (Neg, power' (value1, value2, [1]))

end
