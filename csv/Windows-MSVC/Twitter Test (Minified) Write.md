
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4992.53 | 0.0955837 | 9252.5ms | 475954 | 4890 | 3.69288e+07 | 90916.9 | 0.270676 | 0.49568 | 1(Win) | true |
| Jsonifier DID NOT CONVERGE | 3952.76 | 0.531372 | 6320.09ms | 475954 | 80 | 2.97863e+07 | 114832 | 2.51703 | 0.625854 | -(Loss) | false |
