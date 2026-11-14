
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7343.53 | 0.225785 | 8714.25ms | 631514 | 4890 | 1.6767e+08 | 82012.1 | 0.4359 | 1(Win) | true |
| simdjson (stage-1) | 6132.18 | 0.654294 | 5011.52ms | 631514 | 160 | 6.60696e+07 | 98212.8 | 0.565222 | 2(Loss) | true |
