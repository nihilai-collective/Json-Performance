
----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13313.5 | 0.0607233 | 696.766ms | 94653 | 4890 | 82890.1 | 6780.18 | 0.0445081 | 0.226986 | 1(Win) | true |
| simdjson (stage-1) | 11401.8 | 0.151822 | 803.565ms | 94653 | 640 | 92463.8 | 7917.03 | 0.112622 | 0.265197 | 2(Loss) | true |
