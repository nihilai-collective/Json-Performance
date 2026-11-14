
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20195.1 | 0.0404625 | 390.708ms | 83958 | 80 | 205.886 | 3964.75 | 0.0693132 | 0.121727 | 1(Win) | true |
| simdjson (stage-1) | 18214.2 | 0.0397609 | 422.875ms | 83958 | 30 | 91.6506 | 4395.93 | 0.128741 | 0.134968 | 2(Loss) | true |
