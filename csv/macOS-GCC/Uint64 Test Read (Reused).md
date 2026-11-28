
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1525.29 | 0.82813 | 76.566ms | 1213 | 4890 | 192897 | 758.42 | 4.81681 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 870.159 | 0.528351 | 137ms | 1213 | 4890 | 241256 | 1329.42 | 0.937404 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 866.263 | 1.00786 | 141.71ms | 1213 | 1280 | 231864 | 1335.4 | 1.53589 | 2(Tie) | true |
| simdjson (ondemand) | 320.25 | 0.30457 | 398.072ms | 1213 | 2560 | 309854 | 3612.2 | 0.997643 | 4(Loss) | true |
