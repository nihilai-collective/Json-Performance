
----
### Apache Builds Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 939.045 | 0.245074 | 346.47ms | 3370 | 40 | 2814.1 | 3422.5 | 0.0730994 | 3.21548 | 1(Win) | true |
| simdjson (ondemand) | 642.866 | 0.117154 | 505.713ms | 3370 | 4890 | 167743 | 4999.3 | 0.440921 | 4.71023 | 2(Loss) | true |
