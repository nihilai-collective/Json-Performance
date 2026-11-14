
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2741.51 | 0.309849 | 962.145ms | 25388 | 1280 | 958496 | 8831.6 | 0.812748 | 1(Win) | true |
| Jsonifier (two-stage) | 2304.31 | 1.26433 | 1176.08ms | 25388 | 160 | 2.82369e+06 | 10507.2 | 0.0456621 | 2(Loss) | true |
| simdjson (reflection) | 1944.04 | 0.973705 | 1403.52ms | 25388 | 80 | 1.1765e+06 | 12454.4 | 0.620476 | 3(Loss) | true |
| Glaze | 1658.23 | 0.146393 | 1536.25ms | 25388 | 4890 | 2.23415e+06 | 14601 | 0.0752498 | 4(Loss) | true |
| simdjson (ondemand) | 1369.3 | 0.413492 | 1887.35ms | 25388 | 640 | 3.42119e+06 | 17682 | 1.20905 | 5(Loss) | true |
