
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21152.5 | 0.22613 | 2124.04ms | 461466 | 1280 | 2.83323e+06 | 20805.5 | 0.484481 | 0.116885 | 1(Win) | true |
| simdjson (stage-1) | 17989.7 | 0.0664162 | 2496.95ms | 461466 | 30 | 7919.54 | 24463.3 | 0.122482 | 0.137403 | 2(Loss) | true |
