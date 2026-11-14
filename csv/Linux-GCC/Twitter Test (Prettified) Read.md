
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2455.19 | 0.0714417 | 7255.75ms | 360584 | 1280 | 1.28161e+07 | 140063 | 0.0670144 | 1.00812 | 1(Win) | true |
| Jsonifier (generic) | 2215.37 | 0.338124 | 7987.57ms | 360584 | 40 | 1.10187e+07 | 155224 | 0.209727 | 1.11726 | 2(Loss) | true |
