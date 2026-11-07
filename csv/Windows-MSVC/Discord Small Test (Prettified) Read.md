
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1115.04 | 0.160065 | 616.773ms | 6701 | 80 | 6732.59 | 5731.25 | 0.326087 | 2.2099 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1113.54 | 0.218503 | 588.754ms | 6701 | 2560 | 402551 | 5738.95 | 0.00204201 | 2.21219 | 1(Tie) | true |
| Glaze | 1092.41 | 0.133859 | 607.122ms | 6701 | 160 | 9811.32 | 5850 | 0.106724 | 2.25569 | 3(Loss) | true |
| simdjson (ondemand) | 915.719 | 0.168496 | 730.634ms | 6701 | 80 | 11061.7 | 6978.75 | 0.0896379 | 2.68967 | 4(Loss) | true |
