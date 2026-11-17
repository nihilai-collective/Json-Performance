
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22159.5 | 0.101155 | 248.61ms | 56369 | 320 | 1927.02 | 2425.94 | 0.0644496 | 0.110484 | 1(Win) | true |
| simdjson (stage-1) | 18601.3 | 0.145664 | 293.675ms | 56369 | 80 | 1417.72 | 2890 | 0 | 0.13157 | 2(Loss) | true |
