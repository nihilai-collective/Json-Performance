
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1046.71 | 0.700974 | 116.969ms | 1313 | 2560 | 180021 | 1196.3 | 0.868465 | 1(Win) | true |
| Glaze | 721.299 | 1.45274 | 173.132ms | 1313 | 320 | 203529 | 1736 | 1.40187 | 2(Loss) | true |
| simdjson (reflection) | 579.174 | 0.766722 | 219.361ms | 1313 | 1280 | 351720 | 2162 | 0.259692 | 3(Loss) | true |
| simdjson (ondemand) | 268.592 | 0.345207 | 466.921ms | 1313 | 2560 | 663045 | 4662 | 1.41262 | 4(Loss) | true |
