
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2371.11 | 0.0533083 | 3956.52ms | 65103 | 4890 | 952793 | 26184.8 | 0.212348 | 2.12463 | 7.39511 | 1.0931 | 0.00688614 | 6.609e-05 | 4.21104e-05 | 1(Win) | true |
| Jsonifier | 2264.85 | 0.0220096 | 3953.27ms | 65103 | 4890 | 178015 | 27413.4 | 0.085053 | 2.22124 | 7.42154 | 1.27603 | 0.00258306 | 2.73469e-05 | 1.59477e-05 | 2(Loss) | true |
| simdjson (reflection) | 2234.77 | 0.0351012 | 4111.83ms | 65103 | 2560 | 243456 | 27782.3 | 0.0273503 | 2.26053 | 7.63836 | 1.22003 | 0.00750848 | 7.03573e-05 | 3.84247e-05 | 3(Loss) | true |
| Glaze | 2004.54 | 0.058997 | 4481.07ms | 65103 | 2560 | 854815 | 30973.2 | 0.0296993 | 2.52712 | 8.9377 | 1.70282 | 0.0123088 | 6.43512e-05 | 4.39208e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1939.91 | 0.0446982 | 4492.49ms | 65103 | 2560 | 523913 | 32005.1 | 0.126021 | 2.60147 | 7.8295 | 1.35337 | 0.00786866 | 4.47848e-05 | 2.55365e-05 | 5(Loss) | true |
