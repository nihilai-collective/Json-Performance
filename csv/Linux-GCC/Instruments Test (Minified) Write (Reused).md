
----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 25550.9 | 0.175654 | 413.529ms | 108313 | 2560 | 129094 | 4042.73 | 0.171812 | 0.0962908 | 1(Win) | true |
| simdjson (reflection) | 15101.4 | 0.0952834 | 689.581ms | 108313 | 4890 | 207716 | 6840.11 | 0.0508796 | 0.163333 | 2(Loss) | true |
| Glaze | 2650.8 | 0.174253 | 4048.47ms | 108313 | 640 | 2.95085e+06 | 38967.7 | 0.0912224 | 0.93338 | 3(Loss) | true |
