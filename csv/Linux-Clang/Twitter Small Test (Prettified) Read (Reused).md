
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3556.77 | 0.184351 | 846.238ms | 3808 | 320 | 1133.77 | 1021.04 | 0.517459 | 1.48384 | 4.94643 | 0.840336 | 0.000527672 | 3.69288e-05 | 4.1032e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2830.34 | 0.253818 | 875.517ms | 3808 | 2560 | 27152 | 1283.09 | 0.340056 | 1.82104 | 6.60767 | 0.928047 | 0.000531467 | 3.7134e-05 | 2.0516e-06 | 2(Loss) | true |
| Glaze | 2801.65 | 0.268873 | 870.771ms | 3808 | 640 | 7773.9 | 1296.23 | 0.194296 | 1.8572 | 7.85033 | 1.35662 | 0.000297072 | 3.28256e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 1323.96 | 0.0816862 | 1020.36ms | 3808 | 4890 | 24550 | 2742.98 | 0.332129 | 3.82321 | 13.2014 | 2.10793 | 0.000348099 | 5.72468e-05 | 9.55904e-06 | 4(Loss) | true |
