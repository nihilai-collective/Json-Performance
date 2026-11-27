
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 915.792 | 0.430959 | 102.011ms | 905 | 4890 | 80664.7 | 942.436 | 0.0810017 | 1(Win) | true |
| simdjson (ondemand) | 408.016 | 0.328481 | 212.925ms | 905 | 2560 | 123596 | 2115.3 | 0.0803023 | 2(Loss) | true |
