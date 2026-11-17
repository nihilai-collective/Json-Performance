
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3709.27 | 0.0569523 | 1459.16ms | 25388 | 4890 | 67579.1 | 6527.4 | 0.195093 | 1.37701 | 6.73732 | 1.04171 | 0.00297399 | 1.3347e-05 | 5.88817e-06 | 1(Win) | true |
| Jsonifier | 3069.63 | 0.129018 | 1603.33ms | 25388 | 40 | 4142.31 | 7887.55 | 0.00612743 | 1.65628 | 7.443 | 1.55073 | 0.00432291 | 2.56026e-05 | 1.47708e-05 | 2(Loss) | true |
| Glaze | 2614.99 | 0.0544318 | 1714.48ms | 25388 | 4890 | 124203 | 9258.89 | 0.0330495 | 1.94092 | 9.10391 | 1.77568 | 0.00476465 | 2.13456e-05 | 9.76259e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2281.03 | 0.210224 | 1856.26ms | 25388 | 320 | 159335 | 10614.5 | 0.0519314 | 2.22296 | 9.75808 | 1.52328 | 0.00318581 | 5.53903e-06 | 7.38538e-07 | 4(Loss) | true |
