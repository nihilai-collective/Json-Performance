
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8455.89 | 0.152175 | 5284.97ms | 466906 | 640 | 4.10969e+06 | 52658.7 | 0.332487 | 0.292634 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 8112.7 | 0.7015 | 5270.07ms | 466906 | 40 | 5.92985e+06 | 54886.3 | 0.116908 | 0.305009 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 8088.91 | 0.0840601 | 5579.2ms | 466906 | 2560 | 5.4815e+06 | 55047.8 | 0.00465881 | 0.305934 | 2(Tie) | true |
| simdjson (reflection) | 7741.58 | 0.220876 | 5731.44ms | 466906 | 160 | 2.58236e+06 | 57517.5 | 0.193467 | 0.319664 | 4(Loss) | true |
| Glaze | 3266.96 | 0.0586083 | 7086.35ms | 466906 | 1280 | 8.16771e+06 | 136297 | 0.057037 | 0.75769 | 5(Loss) | true |
