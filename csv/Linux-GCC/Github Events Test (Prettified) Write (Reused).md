
----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17144.5 | 0.12203 | 434.919ms | 78778 | 80 | 2287.63 | 4382.09 | 0.480667 | 0.143386 | 1(Win) | true |
| Glaze | 5916.34 | 0.0965013 | 1275.36ms | 78778 | 4890 | 734309 | 12698.5 | 0.0393541 | 0.417565 | 2(Loss) | true |
| simdjson (reflection) | 674.867 | 0.185505 | 5732.89ms | 78778 | 160 | 6.82344e+06 | 111323 | 0.686223 | 3.66748 | 3(Loss) | true |
