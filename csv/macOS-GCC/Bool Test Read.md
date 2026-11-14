
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1309.28 | 4.17217 | 85.6289ms | 905 | 320 | 242052 | 659.2 | 1.2285 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1253.5 | 0.998518 | 89.066ms | 905 | 4890 | 231136 | 688.53 | 2.18612 | 1(Tie) | true |
| Jsonifier (two-stage) | 320.274 | 0.651129 | 275.862ms | 905 | 1280 | 394092 | 2694.8 | 2.98099 | 3(Loss) | true |
| simdjson (ondemand) | 150.163 | 0.633937 | 590.899ms | 905 | 640 | 849660 | 5747.6 | 1.01268 | 4(Loss) | true |
