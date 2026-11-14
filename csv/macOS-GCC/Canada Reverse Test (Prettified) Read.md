
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 980.143 | 0.576728 | 7791.09ms | 5212421 | 80 | 6.84436e+10 | 5.07166e+06 | 4.61429 | 1(Win) | true |
| Jsonifier (generic) | 932.998 | 1.13797 | 7862.84ms | 5212421 | 30 | 1.10281e+11 | 5.32793e+06 | 0.718488 | 2(Loss) | true |
