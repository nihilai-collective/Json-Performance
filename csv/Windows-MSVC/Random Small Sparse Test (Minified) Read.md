
----
### Random Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1260.33 | 0.14582 | 391.01ms | 4926 | 2560 | 75629.1 | 3727.42 | 0.693115 | 2.39954 | 1(Win) | true |
| simdjson (ondemand) | 1110.07 | 0.0821957 | 441.83ms | 4926 | 4890 | 59169.1 | 4231.98 | 0.0509427 | 2.72479 | 2(Loss) | true |
