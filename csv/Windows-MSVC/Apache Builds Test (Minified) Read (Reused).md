
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1230.42 | 0.120919 | 9102.7ms | 94653 | 4890 | 3.84821e+07 | 73363.5 | 0.0189493 | 2.46923 | 1(Win) | true |
| simdjson (ondemand) | 1060.23 | 0.116164 | 5287.75ms | 94653 | 160 | 1.56506e+06 | 85140 | 0.336543 | 2.86578 | 2(Loss) | true |
