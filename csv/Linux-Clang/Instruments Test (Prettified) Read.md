
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22777.5 | 0.162469 | 772.638ms | 183677 | 1280 | 199823 | 7690.39 | 0.0439052 | 0.108332 | 1(Win) | true |
| simdjson (stage-1) | 20511.1 | 0.163502 | 854.944ms | 183677 | 2560 | 499135 | 8540.16 | 0.107629 | 0.120348 | 2(Loss) | true |
