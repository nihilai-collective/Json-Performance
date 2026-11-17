
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13889.6 | 0.0459981 | 3210.98ms | 466906 | 1280 | 278336 | 32058.3 | 0.0399823 | 0.218539 | 1(Win) | true |
| simdjson (stage-1) | 12072.6 | 0.0228263 | 3714.21ms | 466906 | 30 | 2126.44 | 36883.3 | 0.0902935 | 0.251442 | 2(Loss) | true |
