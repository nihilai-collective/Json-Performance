
----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14164.1 | 2.93427 | 22.39ms | 2866 | 4890 | 156776 | 192.969 | 0.347638 | 1(Win) | true |
| Glaze | 2757.5 | 1.18126 | 99.7588ms | 2866 | 640 | 87739.7 | 991.2 | 0.88 | 2(Loss) | true |
| simdjson (reflection) | 376.946 | 0.124224 | 729.674ms | 2866 | 4890 | 396745 | 7250.98 | 0.523727 | 3(Loss) | true |
