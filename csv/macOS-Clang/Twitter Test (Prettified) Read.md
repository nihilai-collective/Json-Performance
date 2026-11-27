
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2414.63 | 0.155485 | 6734.25ms | 631514 | 160 | 2.40637e+07 | 249421 | 0.0732533 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1985.84 | 0.677918 | 8797.06ms | 631514 | 80 | 3.3816e+08 | 303277 | 0.0303715 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1963.94 | 0.285069 | 7972.67ms | 631514 | 30 | 2.29261e+07 | 306658 | 1.10449 | 2(Tie) | true |
| simdjson (ondemand) | 919.204 | 0.818542 | 8189.94ms | 631514 | 320 | 9.20395e+09 | 655196 | 1.10231 | 4(Loss) | true |
