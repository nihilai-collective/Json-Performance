
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21911.8 | 0.0703632 | 368.8ms | 83958 | 30 | 198.326 | 3654.13 | 0.0355888 | 0.112164 | 1(Win) | true |
| simdjson (stage-1) | 20210 | 0.114232 | 400.806ms | 83958 | 4890 | 100156 | 3961.82 | 0.147967 | 0.121685 | 2(Loss) | true |
