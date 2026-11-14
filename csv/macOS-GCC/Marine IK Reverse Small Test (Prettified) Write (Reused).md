
----
### Marine IK Reverse Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7046.77 | 1.61695 | 291.133ms | 24579 | 160 | 462871 | 3326.4 | 0.431034 | 1(Win) | true |
| Glaze | 3137.43 | 0.781063 | 706.399ms | 24579 | 320 | 1.08969e+06 | 7471.2 | 1.31265 | 2(Loss) | true |
| simdjson (reflection) | 305.236 | 0.268041 | 8005.29ms | 24893 | 640 | 2.7814e+07 | 77775.2 | 0.389294 | 3(Loss) | true |
