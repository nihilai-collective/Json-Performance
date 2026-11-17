
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1670.91 | 0.413648 | 278.342ms | 4669 | 1280 | 155529 | 2664.83 | 0.564433 | 1.46657 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1667.47 | 0.0832225 | 268.902ms | 4669 | 30 | 148.161 | 2670.33 | 0.00998727 | 1.46899 | 1(Tie) | true |
