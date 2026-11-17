
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10252.4 | 0.0533427 | 527.113ms | 56369 | 2560 | 20027.3 | 5243.44 | 0.0104308 | 0.294079 | 1(Win) | true |
| simdjson (stage-1) | 9451.01 | 0.0523715 | 571.82ms | 56369 | 4890 | 43393.4 | 5688.04 | 0.0046305 | 0.319288 | 2(Loss) | true |
