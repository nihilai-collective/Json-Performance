
----
### Apache Builds Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1986.25 | 0.0503232 | 5398.13ms | 94653 | 4890 | 2.55767e+06 | 45446.4 | 0.133479 | 1.52939 | 1(Win) | true |
| simdjson (ondemand) | 1542.88 | 0.0695002 | 6713.17ms | 94653 | 2560 | 4.23269e+06 | 58506.2 | 0.0704214 | 1.96911 | 2(Loss) | true |
