
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 2678.4 | 1.68634 | 52.802ms | 1213 | 4890 | 259400 | 431.902 | 3.40001 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2525.78 | 3.05829 | 57.4531ms | 1213 | 1280 | 251130 | 458 | 0.865801 | 1(Tie) | true |
| Glaze | 969.5 | 1.90123 | 145.293ms | 1213 | 640 | 329364 | 1193.2 | 0.699068 | 3(Loss) | true |
