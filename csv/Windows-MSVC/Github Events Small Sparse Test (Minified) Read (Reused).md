
----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4736.29 | 0.245632 | 38.8198ms | 1691 | 4890 | 3420.5 | 340.491 | 0.00499693 | 0.608627 | 1(Win) | true |
| simdjson (ondemand) | 3603.09 | 0.354974 | 48.9327ms | 1691 | 1280 | 3231.03 | 447.578 | 0.192375 | 0.810875 | 2(Loss) | true |
