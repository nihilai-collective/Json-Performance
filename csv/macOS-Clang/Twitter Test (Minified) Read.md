
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 7514.46 | 0.296476 | 6239.09ms | 466906 | 4890 | 1.50922e+08 | 59255.9 | 1.30152 | 1(Win) | true |
| simdjson (stage-1) | 6096.77 | 1.04646 | 7700.97ms | 466906 | 30 | 1.75236e+07 | 73034.7 | 0.713661 | 2(Loss) | true |
