
----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3002.63 | 0.0895186 | 303.829ms | 8051 | 30 | 157.197 | 2557.1 | 0.0599278 | 0.816586 | 1(Win) | true |
| Jsonifier (two-stage) | 2605.9 | 0.0785009 | 331.236ms | 8051 | 40 | 213.99 | 2946.4 | 0.0656599 | 0.941442 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2242.19 | 0.52285 | 393.256ms | 8051 | 640 | 205159 | 3424.35 | 0.752379 | 1.09575 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2224.57 | 0.146454 | 386.754ms | 8051 | 30 | 766.533 | 3451.47 | 0.103445 | 1.10413 | 3(Tie) | true |
| Glaze | 1852.92 | 0.10818 | 461.691ms | 8051 | 40 | 803.782 | 4143.75 | 0.139373 | 1.32759 | 5(Loss) | true |
