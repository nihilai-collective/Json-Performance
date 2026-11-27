
----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 545.593 | 0.279147 | 5812.24ms | 264040 | 640 | 1.0623e+09 | 461531 | 0.896069 | 5.5702 | 1(Win) | true |
| simdjson (ondemand) | 208 | 0.214911 | 7621.97ms | 264040 | 320 | 2.1661e+09 | 1.21061e+06 | 0.264453 | 14.612 | 2(Loss) | true |
