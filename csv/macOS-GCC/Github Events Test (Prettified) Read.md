
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7613.93 | 0.609175 | 851.204ms | 65103 | 640 | 1.57924e+06 | 8154.4 | 1.35488 | 1(Win) | true |
| simdjson (stage-1) | 6894.35 | 0.251364 | 965.008ms | 65103 | 4890 | 2.50571e+06 | 9005.49 | 0.846523 | 2(Loss) | true |
