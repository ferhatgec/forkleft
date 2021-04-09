# h1: = 'Fegeya ForkLeft (⎇↺↺)'
## h2 := 'Fegeya ForkLeft, C++ implementation of new generation mark-up language that generates HTML code.'

### h3 := 'An example:'
```go
title := 'ForkLeft better'
~= here is comment block.

text ~newline~ := 'hello, text (aka label)'
label ~newline~ := 'hello, label (aka text)'

bold ~newline~ := 'hello, bold'
italic ~newline~ := 'hello, italic'
blockquote ~newline~ := 'hello, blockquote'

link @= ->
    [data
        =path 'https://github.com/ferhatgec/forkleft'
        =text 'Forkleft source code [GitHub]'
    ]
<-

image @= ->
    [data
        =path 'https://octodex.github.com/images/manufacturetocat.png'
        =text 'Octocat lol'
    ]
<-

sign ~newline~ := @copyright@
sign ~newline~ := @trade-mark@
sign ~newline~ := @section@
```

### h3 := 'Features:'
 * Fast, the core library written in C++, header-only.
 * Readable syntax.
 * Specifiers.
 * HTML linker.
 * Inline Kedi tree support.
 * UTF-8 default.

### h3 := 'Fegeya ForkLeft licensed under the terms of MIT License.'
