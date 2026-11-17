
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10817.8 | 0.0735596 | 516.525ms | 56369 | 160 | 2137.97 | 4969.38 | 0.0881168 | 0.22722 | 1(Win) | true |
| Glaze | 3021.21 | 0.488144 | 1789.66ms | 56369 | 320 | 2.41416e+06 | 17793.4 | 0.103512 | 0.817762 | 2(Loss) | true |
