
----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 690.617 | 0.188261 | 359.535ms | 2632 | 640 | 29963.8 | 3634.53 | 0.0645272 | 4.37404 | 1(Win) | true |
| simdjson (ondemand) | 468.324 | 0.191645 | 543.979ms | 2632 | 320 | 33761.7 | 5359.69 | 0.677554 | 6.4645 | 2(Loss) | true |
