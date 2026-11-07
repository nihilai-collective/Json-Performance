
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2727.36 | 0.0565571 | 467.968ms | 9578 | 30 | 107.637 | 3349.13 | 0.0258706 | 0.90102 | 1(Win) | true |
| Glaze | 2027.54 | 0.0463824 | 597.97ms | 9578 | 30 | 130.99 | 4505.1 | 0.148942 | 1.21385 | 2(Loss) | true |
| simdjson (ondemand) | 1617.06 | 0.203485 | 697.664ms | 9578 | 2560 | 338223 | 5648.72 | 0.00864336 | 1.52351 | 3(Loss) | true |
| Jsonifier (two-stage) | 1347.55 | 0.133965 | 808.971ms | 9578 | 2560 | 211098 | 6778.43 | 0.0156772 | 1.83028 | 4(Loss) | true |
