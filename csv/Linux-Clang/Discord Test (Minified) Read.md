
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1440.31 | 0.109444 | 3754.62ms | 56369 | 1280 | 2.13578e+06 | 37323.6 | 0.0459141 | 1.71773 | 1(Win) | true |
| simdjson (ondemand) | 1271.09 | 0.0526664 | 4281.45ms | 56369 | 4890 | 2.42609e+06 | 42292.7 | 0.025123 | 1.94656 | 2(Loss) | true |
