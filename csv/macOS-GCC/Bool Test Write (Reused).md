
----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3146.46 | 3.2479 | 36.894ms | 905 | 2560 | 203188 | 274.3 | 2.19821 | 1(Win) | true |
| simdjson (reflection) | 2470.2 | 1.96145 | 46.3508ms | 905 | 4890 | 229666 | 349.396 | 1.43992 | 2(Loss) | true |
| Glaze | 808.123 | 0.985364 | 125.611ms | 905 | 640 | 70878.7 | 1068 | 1.52091 | 3(Loss) | true |
