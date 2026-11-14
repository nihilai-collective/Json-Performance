
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3130.61 | 0.059363 | 1402.24ms | 18245 | 4890 | 53231.7 | 5557.95 | 0.0290288 | 1.62747 | 6.84988 | 1.22247 | 0.00141295 | 1.06257e-05 | 2.62279e-06 | 1(Win) | true |
| Jsonifier | 2586.26 | 0.210593 | 1506.09ms | 18245 | 1280 | 256947 | 6727.79 | 0.175872 | 1.96705 | 7.58898 | 1.7681 | 0.00204559 | 2.60345e-05 | 7.40785e-06 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2024.84 | 0.0626606 | 1689.47ms | 18245 | 2560 | 74222.8 | 8593.19 | 0.0359258 | 2.50947 | 10.4897 | 2.08556 | 0.00351479 | 1.07906e-05 | 1.39165e-06 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2023.24 | 0.0582906 | 1700.96ms | 18245 | 4890 | 122885 | 8599.96 | 0.147087 | 2.5115 | 10.3714 | 1.69235 | 0.0017471 | 2.85592e-05 | 1.31027e-05 | 3(Tie) | true |
