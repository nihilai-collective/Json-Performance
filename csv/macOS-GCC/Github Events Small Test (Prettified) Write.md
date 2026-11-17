
----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13511.6 | 2.85022 | 23.53ms | 2866 | 4890 | 162556 | 202.287 | 0.841035 | 1(Win) | true |
| Glaze | 2737.61 | 1.23176 | 111.295ms | 2866 | 40 | 6049.48 | 998.4 | 0.847458 | 2(Loss) | true |
| simdjson (reflection) | 360.509 | 0.244343 | 773.777ms | 2866 | 4890 | 1.67813e+06 | 7581.58 | 0.686314 | 3(Loss) | true |
