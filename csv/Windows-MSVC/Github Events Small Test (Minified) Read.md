
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 793.469 | 0.104673 | 207.53ms | 1691 | 2560 | 11586.2 | 2032.42 | 0.331675 | 3.7981 | 1(Win) | true |
| simdjson (ondemand) | 721.36 | 0.133884 | 225.579ms | 1691 | 2560 | 22934 | 2235.59 | 0.266625 | 4.18031 | 2(Loss) | true |
