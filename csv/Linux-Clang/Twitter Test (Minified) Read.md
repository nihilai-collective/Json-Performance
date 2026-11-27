
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 24256.6 | 0.0994799 | 1837.45ms | 466906 | 4890 | 1.63072e+06 | 18356.9 | 0.17094 | 0.101925 | 1(Win) | true |
| simdjson (stage-1) | 20903 | 0.0705002 | 2209.19ms | 466906 | 4890 | 1.10289e+06 | 21302.1 | 0.0462077 | 0.1183 | 2(Loss) | true |
