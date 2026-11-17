
----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 40684.7 | 0.0559813 | 499.516ms | 213963 | 40 | 315.328 | 5015.43 | 0.0330756 | 0.0605144 | 1(Win) | true |
| Glaze | 4165.79 | 0.0637756 | 4901.28ms | 213963 | 4890 | 4.772e+06 | 48982.5 | 0.236447 | 0.594001 | 2(Loss) | true |
| simdjson (reflection) | 507.978 | 0.195098 | 5138.59ms | 213963 | 80 | 4.9134e+07 | 401692 | 0.661681 | 4.87343 | 3(Loss) | true |
