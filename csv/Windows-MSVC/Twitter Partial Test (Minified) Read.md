
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6694.58 | 0.260471 | 6720.08ms | 466906 | 4890 | 1.46771e+08 | 66513 | 1.05035 | 0.453813 | 1(Win) | true |
| Jsonifier (two-stage) | 6452.25 | 0.622338 | 6865.44ms | 466906 | 4890 | 9.01983e+08 | 69011 | 0.413039 | 0.470861 | 2(Loss) | true |
| simdjson (ondemand) | 4248.24 | 0.056618 | 5504.18ms | 466906 | 1280 | 4.50774e+06 | 104814 | 0.0578739 | 0.715283 | 3(Loss) | true |
| Glaze | 2926.91 | 0.423681 | 7972.7ms | 466906 | 160 | 6.6472e+07 | 152132 | 0.633159 | 1.03829 | 4(Loss) | true |
