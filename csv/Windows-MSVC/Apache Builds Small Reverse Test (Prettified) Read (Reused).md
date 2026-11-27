
----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1371.99 | 0.119657 | 266.209ms | 3370 | 320 | 2514.11 | 2342.5 | 0.186418 | 2.19899 | 1(Win) | true |
| simdjson (ondemand) | 795.485 | 0.158834 | 436.879ms | 3370 | 1280 | 52709.9 | 4040.16 | 0.135543 | 3.80291 | 2(Loss) | true |
