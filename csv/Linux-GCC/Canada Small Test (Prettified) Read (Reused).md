
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2189.89 | 0.0405427 | 586.398ms | 11579 | 40 | 167.179 | 5042.52 | 0.344097 | 1.12429 | 1(Win) | true |
| Jsonifier | 2005.24 | 0.127308 | 622.73ms | 11579 | 4890 | 240342 | 5506.88 | 0.0716188 | 1.22834 | 2(Loss) | true |
| Glaze | 1784.66 | 0.0513993 | 712.858ms | 11579 | 80 | 809.164 | 6187.51 | 0.36069 | 1.38167 | 3(Loss) | true |
| simdjson (reflection) | 1772.8 | 0.118557 | 715.006ms | 11579 | 40 | 2181.43 | 6228.9 | 0.0422939 | 1.39054 | 4(Loss) | true |
| simdjson (ondemand) | 1736.63 | 0.144747 | 727.879ms | 11579 | 2560 | 216865 | 6358.64 | 0.0567402 | 1.41948 | 5(Loss) | true |
