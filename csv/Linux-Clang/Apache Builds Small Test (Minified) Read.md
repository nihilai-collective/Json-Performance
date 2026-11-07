
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2651.03 | 0.0363706 | 97.9441ms | 2632 | 320 | 37.9484 | 946.828 | 0.0822499 | 0.908031 | 1(Win) | true |
| Jsonifier (two-stage) | 2535.71 | 0.0604082 | 101.618ms | 2632 | 320 | 114.424 | 989.891 | 0.109665 | 0.949855 | 2(Loss) | true |
| Glaze | 2101.47 | 0.0845105 | 123.115ms | 2632 | 80 | 81.515 | 1194.44 | 0.114201 | 1.15289 | 3(Loss) | true |
| simdjson (ondemand) | 1566.91 | 0.148237 | 164.725ms | 2632 | 40 | 225.558 | 1601.92 | 0.114055 | 1.55433 | 4(Loss) | true |
