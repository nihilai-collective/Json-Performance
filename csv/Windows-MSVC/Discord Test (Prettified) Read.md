
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1386.44 | 0.288629 | 5924.44ms | 83958 | 320 | 8.89103e+06 | 57751.2 | 0.378039 | 1.78487 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 1316.22 | 0.131179 | 6153.68ms | 83958 | 2560 | 1.63016e+07 | 60832 | 0.203264 | 1.8801 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1316.14 | 0.137869 | 6174.67ms | 83958 | 1280 | 9.00462e+06 | 60836.1 | 0.776757 | 1.88026 | 2(Tie) | true |
| simdjson (ondemand) | 1012.02 | 0.323866 | 8140.58ms | 83958 | 160 | 1.0505e+07 | 79117.5 | 0.552855 | 2.44564 | 4(Loss) | true |
