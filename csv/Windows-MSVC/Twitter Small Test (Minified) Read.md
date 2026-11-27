
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1469.42 | 0.373526 | 198.469ms | 2889 | 80 | 3924.05 | 1875 | 0 | 1.65951 | 1(Win) | true |
| Glaze | 1166.15 | 0.25497 | 241.664ms | 2889 | 4890 | 177449 | 2362.62 | 0.066195 | 2.09563 | 2(Loss) | true |
| Jsonifier (two-stage) | 1119.21 | 0.243836 | 260.091ms | 2889 | 4890 | 176187 | 2461.7 | 0.111821 | 2.1852 | 3(Loss) | true |
| simdjson (ondemand) | 1070.49 | 0.274248 | 274.591ms | 2889 | 80 | 3985.76 | 2573.75 | 0.0485437 | 2.28104 | 4(Loss) | true |
