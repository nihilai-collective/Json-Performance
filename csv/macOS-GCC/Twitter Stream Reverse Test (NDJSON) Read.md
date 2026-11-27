
----
### Twitter Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 635.875 | 0.34313 | 9945.1ms | 4219120 | 80 | 3.77145e+10 | 6.32776e+06 | 1.16517 | 1(Win) | true |
| simdjson (ondemand) | 289.397 | 0.700682 | 10424.9ms | 4219120 | 40 | 3.79628e+11 | 1.39036e+07 | 1.3642 | 2(Loss) | true |
