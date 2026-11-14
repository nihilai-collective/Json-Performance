
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 811.771 | 0.221413 | 6692.39ms | 56369 | 2560 | 5.50376e+07 | 66222.7 | 0.0453222 | 3.04834 | 1(Win) | true |
| simdjson (ondemand) | 740.285 | 0.538329 | 7572.66ms | 56369 | 40 | 6.11276e+06 | 72617.5 | 0.318889 | 3.34264 | 2(Loss) | true |
